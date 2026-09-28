const http = require('http');
const fs = require('fs');

const betterLog = require('./betterLog');

const rootDir = __dirname + "/file";

const server = http.createServer((req, res) => {
    //console.log(`Received request for ${req.url}`);
    betterLog.debug(`Handling request for ${req.url}`);
    fs.readFile(rootDir + req.url, 'utf8', (err, data) => {
        if (err) {
            //console.error(err);
            betterLog.error(`File not found: ${req.url}`);
            res.statusCode = 404;
            res.setHeader('Content-Type', 'text/plain');
            res.end('File not found');
        } else {
            console.log(`Serving file: ${req.url}`);
            res.statusCode = 200;
            res.setHeader('Content-Type', 'text/plain');
            res.end(data);
        }


    });

    //res.statusCode = 200;
    //res.setHeader('Content-Type', 'text/plain');
    //res.end('Hello, ES3!');
});


const PORT = 8080;

server.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}/`);
});