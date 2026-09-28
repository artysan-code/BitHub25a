const fs = require('fs');

fs.readFile('data.txt', 'utf8', (err, data) => {
    if (err) {
        console.error(err);
        return;
    }
    console.log(data);
});


//const data = fs.readFileSync('data.txt', 'utf8');
//console.log(data);

console.log("Fine Script ES2!");