import { Head } from "$fresh/runtime.ts";
import { Chart } from "https://deno.land/x/fresh_charts/mod.ts";
import { ChartColors, transparentize } from "https://deno.land/x/fresh_charts/utils.ts";

export default function DataPlot(props){
  return (<Chart
      type="line"
      data={{
        labels: props.label,
        datasets: [{
          label: "Humedad",
          data: props.data,
          borderColor: ChartColors.Red,
          backgroundColor: transparentize(ChartColors.Red, 0.5),
          borderWidth: 2,
        }],
      }}
  />);
}
