import { Line, mixins } from 'vue-chartjs'
import ChartJsAnnotation from 'chartjs-plugin-annotation'
const { reactiveProp } = mixins

// Chart.plugins.register(ChartJsAnnotation)

export default {
  extends: Line,
  mixins: [reactiveProp],
  props: ['chartData', 'options'],
  mounted () {
    this.addPlugin(ChartJsAnnotation)
    console.log('LineChart mounted data ', this.chartData)
    this.renderChart(this.chartData, this.options)
  }
}