"use strict";

const wishList = document.getElementById("wish-list");
const addItemButton = document.getElementById("add-item");

function addWish() {

    const newWish = prompt("Enter a new wish:");

    if (newWish) {
        const newListItem = document.createElement("li");
        //newListItem.textContent = newWish;
        const txt = document.createTextNode(newWish);
        newListItem.appendChild(txt);

        wishList.appendChild(newListItem);
    }
}

addItemButton.addEventListener("click", addWish);