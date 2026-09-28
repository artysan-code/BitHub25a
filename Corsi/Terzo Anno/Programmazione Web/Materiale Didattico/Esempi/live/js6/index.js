const express = require('express');
const dotenv = require('dotenv');
const morgan = require('morgan');
const fs = require('fs');
dotenv.config();


const app = express();
app.use(morgan('dev'));

app.use(express.json());

const PORT = process.env.PORT || 3000;

const basePath = '/api/v1';


const corsiTxt = fs.readFileSync('./corsi.json', 'utf-8');
const corsi = JSON.parse(corsiTxt);



app.get(`${basePath}/corsi`, (req, res) => {
    res.json(corsi);
});

app.get(`${basePath}/corsi/:id`, (req, res) => {
    const id = parseInt(req.params.id);
    const corso = corsi.find(c => c.id === id);
    if (corso) {
        res.json(corso);
    }
    else {
        res.status(404).json({ message: 'Corso non trovato' });
    }
});


app.post(`${basePath}/corsi`, (req, res) => {
    const { nome, descrizione } = req.body;
    const newCorso = {
        id: corsi.length + 1,
        nome,
        descrizione
    };
    corsi.push(newCorso);
    fs.writeFileSync('./corsi.json', JSON.stringify(corsi, null, 2));
    res.status(201).json(newCorso);
});


app.delete(`${basePath}/corsi/:id`, (req, res) => {
    const id = parseInt(req.params.id);

    console.log(`ID da eliminare: ${id}`);

    const index = corsi.findIndex(c => c.id === id);
    if (index !== -1) {
        const deletedCorso = corsi.splice(index, 1);
        fs.writeFileSync('./corsi.json', JSON.stringify(corsi, null, 2));
        res.status(204).json(deletedCorso[0]);
    }
    else {
        res.status(404).json({ message: 'Corso non trovato' });
    }
});

/* per test */

app.get('/', (req, res) => {
  res.send('Hello World!');
});

app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});