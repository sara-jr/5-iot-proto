'use strict';

let chart = null;
let latest = null;

function makePlot(){
  /*
  const data = [
    {x:0,y:0},
    {x:2,y:4},
    {x:3,y:9},
    {x:4,y:16},
    {x:5,y:25},
    {x:6,y:36},
  ]
  */

  chart = new Chart(document.querySelector('#sensor-plot'),{
    type:'line',
    data:{
      labels:[],
      datasets:[
        {label:'Autos', data:[]}
      ]
    }
  }
  );
}

function updatePlot(id){
  fetch('/api/dummysensors')
  .then((response)=>
    response.json()
  ).then((data)=>{
    chart.data.labels = data.map((item)=>item.date);
    chart.data.datasets.forEach((dataset)=>dataset.data = data.map((item)=>item.measured));
    chart.update();
  });
}

window.addEventListener('load', ()=>{
  makePlot();
});