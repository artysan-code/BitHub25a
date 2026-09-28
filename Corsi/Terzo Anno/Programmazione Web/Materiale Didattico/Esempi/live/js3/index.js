const betterLog = require('./betterLog');

const moment = require('moment');
const dotenv = require('dotenv');

const oraVecchia = require('./oraVecchia');

dotenv.config();

console.log(`Hello ${process.env.HELLO}`)


console.log(moment().format("HH:mm"))

console.log("Hello world")

console.log(oraVecchia())

const oraNuova = require('./oraVecchia');

setTimeout(() => {console.log(oraNuova())},10000)