const express = require('express');
const Router = require('./src/routes/mainRouter.js');
const port = process.env.PORT || 3000;
const app = express();

app.use(Router);
app.use(express.json);
app.listen(port, ()=> {
    console.log(`O servidor está rodando na porta ${port}`);
});