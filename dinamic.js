/*
   This file is part of 'DinamiContent'.

   'DinamiContent' is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License,
   or any later version.

   'DinamiContent' is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with 'IngUnisannio'.  If not, see <http://www.gnu.org/licenses/>.

AUTHOR:  Stefano Viola (estebanSannin) 
CONTACT: stefanoviola [at] sanniolug [dot] org
SITE:    http://estban.homelinux.org

 */

function test(url, id){
	var xmlhttp=false;
	
	/*
	 * Adding IE compatibility...
	 *
	 */
	
	if (!xmlhttp && typeof XMLHttpRequest!='undefined') {
		try {
			xmlhttp = new XMLHttpRequest();
		} catch (e) {
			xmlhttp=false;
		}
	}
	if (!xmlhttp && window.createRequest) {
		try {
			xmlhttp = window.createRequest();
		} catch (e) {
			xmlhttp=false;
		}
	}

	xmlhttp.open("GET", url, true);
	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4) {
			document.getElementById(id).innerHTML = "" + xmlhttp.responseText;
			//alert(xmlhttp.responseText)
		}
	}
	xmlhttp.send(null)
}
var webDinamic = {
interval: '',

	  putCgiContent: function(url, id){
		  //alert(url+" "+id)
		  var req = new XMLHttpRequest();
		  req.open('GET', url, false);
		  req.send(null);
		  //alert("pippo");
		  if(req.readyState == 4){
			  if(req.status == 200){
				  if(id == "textarea"){
					  document.form.textarea.value = req.responseText;
					  //alert(req.responseText);
				  }else{
					  document.getElementById(id).innerHTML = "" + req.responseText;
					  //alert(req.responseText);
				  }
			  }else{
				  alert("Error!");
			  }
		  }


	  },

	  //preleva i parametri da una form e li invia al cgi
xmlhttpGET: function(strURL){

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
		    self.xmlHttpReq.send(null)
	    },
updatePage: function(str){
	    },
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
