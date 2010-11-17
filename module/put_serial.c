#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 *  Author:  Stefano Viola aka (estebanSannin)
 * Contact:  stefanoviola[@]sannioglug[.]org
 * License:  GPLv3
 *
 */
#define INTERFACE ttyUSB1
// Funzione che converte eventuali caratteri speciali
// all'interno della stringa inserita dall'utente in
// caratteri ASCII leggibili
// Prende come parametri la stringa sorgente, la stringa
// di destinazione e la lunghezza della stringa da 'uncodare'
void unencode (char *src, char *dest, int len);


// Funzione per il prelevamento di
// un campo da una query
// Prende come parametri la query in cui cercare
// e il nome del campo da cercare (in questo caso 'nome')
char* get_field(char *query, char *field);

//Funzione che invia comandi sulla seriale
int command_serial(char *command);

//Funzione che invia comandi generici alla consol
int command_shell(char *command);


int main() {
	char *query,*nome;
	int len;
	// Genero la pagina HTML
	printf ("Content-type: text/html\n\n");

	// Se la richiesta GET non contiene niente, la pagina è stata richiamata
	// in modo errato, quindi esco
	if ((query=getenv("QUERY_STRING"))==NULL) {
		printf ("<h3>ERROR!!!</h3>\n"
				"</body></html>\n");
		exit(1);
	}

	// Controllo la lunghezza della query e
	// genero una stringa lunga quanto la query
	// che conterrà il nome inserito dall'utente
	// Ricordiamo che query ora sarà una stringa
	// del tipo 'nome=pippo'
	len=strlen(query);
	nome = (char*) malloc(len*sizeof(char));
	// Ora nome conterrà il campo 'nome' della query
	nome=get_field (query,"nome");
	printf("<html><body>insert %s in dev/ttyS0 <pre>\n",nome);

	command_serial(nome);
	printf("</pre></body></html>\n");
	exit(0);
	return 0;
}

char* get_field(char *query, char *field){
	int i,j,len,pos;
	char *tmp,*input;

	// len è pari alla lunghezza della querry+1
	len = strlen(query)+1;
	
	// tmp sarà il pattern di ricerca all'interno della query
	// Nel nostro caso andrà a contenere la stringa 'nome='
	tmp = (char*) malloc( (strlen(field)+1)*sizeof(char) );
	
	// input è lunga quanto la query, e andrà a contenere
	// il campo da noi ricercato
	input = (char*) malloc(len*sizeof(char));
	
	// tmp <- nome=pippo
	sprintf (tmp, "%s=", field);
	
	// Se all'interno della query non c'è il campo richiesto, esco
	if (strstr(query,tmp)==NULL)
		return NULL;
	
	// Cerco la posizione all'interno della query
	// in cui è stato trovato il campo nome
	pos = ( (int) strstr(query,tmp) - (int) query) + (strlen(field)+1);
	
	// Controllo quanto è lungo il pattern nome=blablabla
	// Questo ciclo termina quando viene incontrato un '&' all'interno
	// della query (ovvero quando comincia un nuovo campo) o quando la stringa è terminata
	// Alla fine i conterrà il numero di caratteri totali nel pattern di ricerca
	for (i=pos; ; i++) {
		if (query[i]=='\0' || query[i]=='&') break;
	}
	
	// Salvo il contenuto della query che mi interessa in input
	for (j=pos; j<i; j++)
		input[j-pos]=query[j];
	
	// 'unencodo' input, rendendo eventuali caratteri speciali umanamente leggibili
	unencode(input,input,len);
	
	// Ritorno input
	return input;
}

void unencode(char *src, char *dest, int len){
	int i,code;

	// Ciclo finché non ho letto tutti i caratteri specificati
	for (i=0; i<len; i++, src++, dest++) {
		// Se il carattere corrente di src è un '+', lo converto in uno spazio ' '
		if (*src=='+') *dest=' ';
		// Se il carattere corrente è un '%'
		else if (*src=='%') {
			// Se il carattere successivo non è un carattere valido,
			// il carattere di destinazione sarà un '?',
			// altrimenti sarà il carattere ASCII corrispondente
			if (sscanf(src+1, "%2x", &code) != 1) code='?';
			*dest = (char) code;
			// Leggo il prossimo carattere
			src += 2;
		}
		// Se è un carattere alfanumerico standard e non un carattere speciale,
		// allora il carattere di destinazione è uguale a quello sorgente
		else *dest=*src;
	}

	// Termino la stringa di destinazione
	dest[len]='\0';
}

int command_shell(char *command){
	FILE *fp;
	char line[1024];
	int iRet = 0;
	fp = popen(command, "r");
	//printf("command: %s\n",command);
	if (fp != NULL){
		while (fgets(line, sizeof(line), fp)){
			printf("%s", line);
		}
		pclose(fp);
		iRet = 0;
	} else {
		iRet = -1;
	}
	return iRet;
}

//funzione per inviare stringhe alla seriale
int command_serial(char *command){
	FILE *fp;
	char line[1024];
	int iRet = 0;
	char temp[50];
	strcpy(temp,"echo ");
	strcat(temp,command);
	strcat(temp," >> serial.log");
	//strcat(temp, interface);
	fp = popen(temp, "r");
	//printf("Command: %s\n",temp);
	//system("echo -n 1 >> /dev/ttyUSB1");
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {
			printf("%s", line);
		}
		//	printf("Command Succesfull!!\n");
		pclose(fp);
		iRet = 0;
	} else {
		iRet = -1;
	}
	return iRet;

}

