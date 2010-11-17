function contentDinamic(url, id){

	var reqLocal = new XMLHttpRequest();
	var req = new XMLHttpRequest();  
	req.open('GET', url, false);   
	req.send(null);
	if(req.status == 200){
		if(id == "dmesg" || id == "serial"){
			document.form.textarea.value = req.responseText;
		}else{
			document.getElementById(
					id).innerHTML = "" + req.responseText;
		}	
	}  

	else{
		//alert("Error loading page Req status:" + req.status + " and url: " + url);  
		document.getElementById(
				id).innerHTML = "Error Loding!";
	}
}
function reset(id){
	document.getElementById(id).innerHTML = ""
}

//preleva i parametri da una form e li invia al cgi
function xmlhttpGET(strURL) {
	var xmlHttpReq = false;
	var self = this;
	// Xhr per Mozilla/Safari/Ie7
	if (window.XMLHttpRequest) {
		self.xmlHttpReq = new XMLHttpRequest();
	}
	// per tutte le altre versioni di IE
	else if (window.ActiveXObject) {
		self.xmlHttpReq = new ActiveXObject("Microsoft.XMLHTTP");
	}
	self.xmlHttpReq.open('GET', strURL+"?"+getquerystring(), true);
	self.xmlHttpReq.setRequestHeader('Content-Type', 'application/xhtml+xml');
	self.xmlHttpReq.onreadystatechange = function() {
		if (self.xmlHttpReq.readyState == 4) {
			updatepage(self.xmlHttpReq.responseText);
		}
	}
	self.xmlHttpReq.send(null);
}

function updatepage(str){
	document.getElementById("result").innerHTML = str;
}

function mostraOra(){
	document.getElementById(
			"ora").innerHTML = ""+new Date()
}
function getquerystring() {
	var form     = document.forms['f1'];
	var nome = form.nome.value;
	qstr = 'nome=' + escape(nome);
	return qstr;
}


//mostraOra();
