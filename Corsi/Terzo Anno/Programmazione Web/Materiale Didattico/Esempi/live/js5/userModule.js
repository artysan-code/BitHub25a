const express = require('express');
const userRouter = express.Router();

userRouter.get('/login', (req, res) => {
    res.send("Login page");
});

userRouter.get('/register', (req, res) => {
    res.send("Register page");
});

userRouter.get('/logout', (req, res) => {
    res.send("Logout page");
});

module.exports = userRouter;