import { Head } from "$fresh/runtime.ts";
import  DataPlot  from "../islands/DataPlot.tsx";


export const handler: Handlers<Array> = {
  async GET(_, context){
    const latest = await fetch('http://localhost:8000/api/sensors');
    const data = await latest.json();
    return context.render(data);
  }
}

export default function Home(props: PageProps<Array>) {
  return (
    <>
      <Head>
        <title>Monitor de Sensores de trafico</title>
      </Head>
      <div class="p-4 mx-auto max-w-screen-md">
        <DataPlot
          data={props.data.map((x)=>x['measured'])}
          label={props.data.map((x)=>x['date'])}
        />
      </div>
      <footer class="bg-black grid grid-cols-2">
        <img
          src="/logo.svg"
          class="w-16 h-16"
          alt="the fresh logo: a sliced lemon dripping with juice"
        />
        <p class="my-6 text-white">
          Funcionando gracias a "fresh"
        </p>
      </footer>
    </>
  );
}

