import express from 'express';
const app = express();
const port = 3000;
app.get('/', (_, res)=>
{
     res.send('Hello World');
});
 app.listen(port, ()=>{
     console.log(
`Connected successfully on port http://localhost:${port}`)
});