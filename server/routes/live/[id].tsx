import { PageProps } from "$fresh/server.ts";
import { Head } from "$fresh/runtime.ts";
import { asset } from "$fresh/runtime.ts";

export default function LivePage(props: PageProps){
  const {id} = props.params;
  return (<>
    <Head>
      <title> Sensor: {id} </title>
      <script type='application/javascript' src='https://cdn.jsdelivr.net/npm/chart.js'></script>
      <script src={asset('/live-sensor.js')}></script>
    </Head>
    <button 
      id='reload-button'
      onClick={`updatePlot('${id}')`}>
      Actualizar
    </button>
    <canvas id='sensor-plot'></canvas>
  </>);
}