
export default function DataPlot(){
  <Chart
    type='line'

    data={{
      labels: ['Humedad'],
      datasets: [{
        label: 'Humedad',
        data: []
      }]
    }} 
  />
}
