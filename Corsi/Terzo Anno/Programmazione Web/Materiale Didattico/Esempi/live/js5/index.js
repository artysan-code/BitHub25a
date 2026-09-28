const express = require('express');
const app = express();
const morgan = require('morgan');
const cors = require('cors');


app.use(cors());
app.use(morgan('dev'));

app.use((req, res,next) => {
    console.log(`Request received: ${req.method} ${req.url}`);
    next();
});


app.use(express.static('public'));
app.use(express.json());


app.get('/', (req, res) => {
  res.send('Hello, World!');
});

app.post('/', (req, res) => {

    res.status(201).send('Form submitted successfully!');
});


app.get('/about', (req, res) => {
    res.send("About us page");
});

app.get('/api', (req, res) => {
    res.json({ message: "This is a JSON response" });
});

app.get('/about/:id', (req, res) => {
    console.log(req.params);
    if(req.params.id === "pierpaolo"){
        res.send("Info su Pierpaolo!");
    } else {
        res.status(404).send("Page not found");
    }
});

const PORT = 8080;


const userRouter = require('./userModule');
app.use('/users', userRouter);




app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});