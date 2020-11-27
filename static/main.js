//GLOBAL VARIABLES
var word;
var displayWord = [""];
var size = 0;
var image = 0;

$(document).ready(function(){
	initial(); //INITIAL PIC IS LOADED 1st
	makeButtonsOpaque(); //Ensures you cannot press buttons until game is started
});

function initial(){
	size = 0;
	image = 0;
	$.get("/initial", {}, function(response){
		var data;
		var htmlCode = "";
		data = JSON.parse(response);
		htmlCode = "";
		for (var i in data){
			var currentList = data[i];
			var filename = currentList[0];
			htmlCode += '<img style="width:250px;height:450px;"src="images/' + filename + '">';
		}
		$("#pictureArea").html(htmlCode);
	});
}

function clickStartGame(){ 
	document.getElementById('START').innerHTML = "RESTART";
	resetButtons();
	displayWord = [""];
	size = 0;
	allFound = "";
	initial();
	$.get("/startGame", {}, function(response){ 
		word = JSON.parse(response);
		for(var i = 0; i < word["length"]; i++){
			displayWord[i] = "_ ";
		}
		console.log(word["fullWord"]);
		$("#underscores").html(displayWord);
		$("#category").html("CATEGORY: " + word["category"]);
	});
}

function clickLetter(letter){
	$.get("/checkLetter",{"theLetter": letter}, function(response){
		let check = JSON.parse(response);
		if(check["hasLetter"] == true){
			for(var i = 0; i < word["length"]; i++){
				if(i == check.location[size]){
					size++;
					displayWord[i] = word.fullWord[i] + " ";
				}
			}
		}
		else{
			image++;
			$.get("/getDrawings", {}, function(response){
				let drawing = JSON.parse(response);
				let htmlCode = "";
				let letters = "";
				for (var i in drawing){
					var currentDrawing = drawing[i];
					var filename = currentDrawing[image];
					htmlCode += '<img style="width:250px;height:450px;"src="images/' + filename + '">';
				}
				for(i in check["lettersGuessed"]){
					letters += check.lettersGuessed[i];
				}
				$("#pictureArea").html(htmlCode);
				$("#lettersGuessed").html("LETTERS GUESSED INCORRECTLY: " + letters);
			});
		}
		if(size == word["length"]){
			allFound = "YOU WIN! THE WORD WAS " + word["fullWord"] + "!";
			$("#underscores").html(allFound);
			makeButtonsOpaque();
			return;
		}
		if(image == 6){
			makeButtonsOpaque();
			youLost = "YOU LOST! THE WORD WAS " + word["fullWord"] + "!";
			$("#underscores").html(youLost);
			return;
		}
		$("#underscores").html(displayWord);
	});
}

function makeButtonsOpaque(){
	document.getElementById('A').disabled = true;
	document.getElementById('A').style.opacity='0.5';
	document.getElementById('B').disabled = true;
	document.getElementById('B').style.opacity='0.5';
	document.getElementById('C').disabled = true;
	document.getElementById('C').style.opacity='0.5';
	document.getElementById('D').disabled = true;
	document.getElementById('D').style.opacity='0.5';
	document.getElementById('E').disabled = true;
	document.getElementById('E').style.opacity='0.5';
	document.getElementById('F').disabled = true;
	document.getElementById('F').style.opacity='0.5';
	document.getElementById('G').disabled = true;
	document.getElementById('G').style.opacity='0.5';
	document.getElementById('H').disabled = true;
	document.getElementById('H').style.opacity='0.5';
	document.getElementById('I').disabled = true;
	document.getElementById('I').style.opacity='0.5';
	document.getElementById('J').disabled = true;
	document.getElementById('J').style.opacity='0.5';
	document.getElementById('K').disabled = true;
	document.getElementById('K').style.opacity='0.5';
	document.getElementById('L').disabled = true;
	document.getElementById('L').style.opacity='0.5';
	document.getElementById('M').disabled = true;
	document.getElementById('M').style.opacity='0.5';
	document.getElementById('N').disabled = true;
	document.getElementById('N').style.opacity='0.5';
	document.getElementById('O').disabled = true;
	document.getElementById('O').style.opacity='0.5';
	document.getElementById('P').disabled = true;
	document.getElementById('P').style.opacity='0.5';
	document.getElementById('Q').disabled = true;
	document.getElementById('Q').style.opacity='0.5';
	document.getElementById('R').disabled = true;
	document.getElementById('R').style.opacity='0.5';
	document.getElementById('S').disabled = true;
	document.getElementById('S').style.opacity='0.5';
	document.getElementById('T').disabled = true;
	document.getElementById('T').style.opacity='0.5';
	document.getElementById('U').disabled = true;
	document.getElementById('U').style.opacity='0.5';
	document.getElementById('V').disabled = true;
	document.getElementById('V').style.opacity='0.5';
	document.getElementById('W').disabled = true;
	document.getElementById('W').style.opacity='0.5';
	document.getElementById('X').disabled = true;
	document.getElementById('X').style.opacity='0.5';
	document.getElementById('Y').disabled = true;
	document.getElementById('Y').style.opacity='0.5';
	document.getElementById('Z').disabled = true;
	document.getElementById('Z').style.opacity='0.5';
}

function resetButtons(){
	document.getElementById('A').disabled = false;
	document.getElementById('A').style.opacity='1';
	document.getElementById('B').disabled = false;
	document.getElementById('B').style.opacity='1';
	document.getElementById('C').disabled = false;
	document.getElementById('C').style.opacity='1';
	document.getElementById('D').disabled = false;
	document.getElementById('D').style.opacity='1';
	document.getElementById('E').disabled = false;
	document.getElementById('E').style.opacity='1';
	document.getElementById('F').disabled = false;
	document.getElementById('F').style.opacity='1';
	document.getElementById('G').disabled = false;
	document.getElementById('G').style.opacity='1';
	document.getElementById('H').disabled = false;
	document.getElementById('H').style.opacity='1';
	document.getElementById('I').disabled = false;
	document.getElementById('I').style.opacity='1';
	document.getElementById('J').disabled = false;
	document.getElementById('J').style.opacity='1';
	document.getElementById('K').disabled = false;
	document.getElementById('K').style.opacity='1';
	document.getElementById('L').disabled = false;
	document.getElementById('L').style.opacity='1';
	document.getElementById('M').disabled = false;
	document.getElementById('M').style.opacity='1';
	document.getElementById('N').disabled = false;
	document.getElementById('N').style.opacity='1';
	document.getElementById('O').disabled = false;
	document.getElementById('O').style.opacity='1';
	document.getElementById('P').disabled = false;
	document.getElementById('P').style.opacity='1';
	document.getElementById('Q').disabled = false;
	document.getElementById('Q').style.opacity='1';
	document.getElementById('R').disabled = false;
	document.getElementById('R').style.opacity='1';
	document.getElementById('S').disabled = false;
	document.getElementById('S').style.opacity='1';
	document.getElementById('T').disabled = false;
	document.getElementById('T').style.opacity='1';
	document.getElementById('U').disabled = false;
	document.getElementById('U').style.opacity='1';
	document.getElementById('V').disabled = false;
	document.getElementById('V').style.opacity='1';
	document.getElementById('W').disabled = false;
	document.getElementById('W').style.opacity='1';
	document.getElementById('X').disabled = false;
	document.getElementById('X').style.opacity='1';
	document.getElementById('Y').disabled = false;
	document.getElementById('Y').style.opacity='1';
	document.getElementById('Z').disabled = false;
	document.getElementById('Z').style.opacity='1';
}


