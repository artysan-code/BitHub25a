"use strict";

function haiVinto(e) {
    alert('Hai vinto');
}
const targetDiv = document.getElementById('clickme');
const body = document.body; // document.getElementsByTagName('body')[0];

// inizializziamo i colori 
targetDiv.style.backgroundColor = 'black';
body.style.backgroundColor = 'white';

let divIsBlack = true;

function moveTheDiv() {
    if (divIsBlack) {
        targetDiv.style.backgroundColor = 'white';
        body.style.backgroundColor = 'black';
    } else {
        targetDiv.style.backgroundColor = 'black';
        body.style.backgroundColor = 'white';
    }

    divIsBlack = !divIsBlack;
    targetDiv.style.marginLeft = Math.random() * 500 + 'px';
    targetDiv.style.marginTop = Math.random() * 500 + 'px';
}

targetDiv.addEventListener('click', haiVinto);

const MY_INTERVAL = 500;

setInterval(moveTheDiv, MY_INTERVAL);