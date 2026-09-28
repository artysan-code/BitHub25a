const moment = require('moment');
const now = moment().format('YYYY-MM-DD HH:mm:ss');

console.log(`Ora vecchia: ${now}`);

module.exports = function oraVecchia() {
    return now;
}