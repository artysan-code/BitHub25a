"use strict";

let promise = new Promise((resolve, reject) => {
    
    setTimeout(() => {
        if (Math.random() > 0.5) {
            reject(new Error("Something went wrong!"));
        } else {
            resolve("done!");
        }
    }, 10000);
}); 
console.log(promise); // Promise { <pending> }


//let output = promise.then(result => console.log(result), error => console.error(error)).finally(() => console.log("Finally!")); // done! (after 10 seconds)
let output = promise.then(result => console.log(result)).catch(error => console.error(error)).finally(() => console.log("Finally!")); // done! (after 10 seconds)