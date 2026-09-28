"use strict";

const homerImages = [
    "https://static.wikia.nocookie.net/simpsons/images/6/67/S34E19_Write_Off_This_Episode_-_Homer.png/revision/latest/scale-to-width-down/1000?cb=20260201075614",
    "https://static.wikia.nocookie.net/simpsons/images/a/ad/Sleepinchruch.jpg/revision/latest?cb=20191031221654",
    "https://static.wikia.nocookie.net/simpsons/images/f/fb/Homerdonut.jpg/revision/latest?cb=20070718203904"
];

const myImage = document.getElementById("my-image");
const changeImgBtn = document.getElementById("change-img");
let imgIdx = 0;

changeImgBtn.addEventListener("click", () => {
    //myImage.src = homerImages[imgIdx];
    myImage.setAttribute("src", homerImages[imgIdx]);
    imgIdx = (imgIdx + 1) % homerImages.length;
});