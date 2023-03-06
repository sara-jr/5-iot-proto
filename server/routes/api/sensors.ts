import Surreal from "https://deno.land/x/surrealdb/mod.ts";
import { format } from "https://deno.land/std@0.91.0/datetime/mod.ts";
import { HandlerContext, Handlers } from "$fresh/server.ts";

const db = new Surreal('http://127.0.0.1:8001/rpc');

async function connect(){
  try{
    await db.signin({user:'root', pass:'root123q'});
    await db.use('global', 'sensors');
  }
  catch(error){
    console.log('Error al conectarse a la BDD: ', error);
  }
}

export const handler: Handlers = {
  GET: async (req: Request, ctx: HandlerContext) => {
    const latest = await db.query('select * from sensors');
    return Response(null, {status: 200, statusText:'Data recived'});
  },

  POST: async (req: Request, ctx: HandlerContext) => {
    await connect();
    console.log('DATA RECIVED!!');
    try{
      let data = await req.json();
      let record = await db.create('message', {
        date: format(new Date(), 'yyyy-MM-dd HH:mm:ss'),
        value: data
      });
      console.log(data);
      console.log(record);
    }
    catch(error){
      console.log(error);
      return new Response(null, {status: 400, statusText:'Error'});
    }

    return new Response(null, {status: 200, statusText:'Data recived'});
  }
}
