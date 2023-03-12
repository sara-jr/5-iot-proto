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
    const latest = await db.query('select * from message order by date limit 50');
    
    return new Response(JSON.stringify(latest[0]['result']), {
      status: 200, statusText:'Data sent', 
      headers:{'content-type':'aplication/json'}
    });
  },

  POST: async (req: Request, ctx: HandlerContext) => {
    await connect();
    console.log('DATA RECIVED!!');
    try{
      let data = await req.json();
      let record = await db.create('message', {
        date: format(new Date(), 'yyyy-MM-dd HH:mm:ss'),
        sensor_id: data['id'],
        measured: data['humidity']
      });
    }
    catch(error){
      console.log(error);
      return new Response(null, {status: 400, statusText:'Error'});
    }

    return new Response(null, {status: 200, statusText:'Data recived'});
  }
}
