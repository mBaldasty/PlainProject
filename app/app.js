import Vue from 'nativescript-vue'

import Home from './components/Home'
Vue.registerElement('CameraView', () => require('@nativescript-community/ui-cameraview').CameraView)
import {CropView} from "~/components/CropView";
Vue.registerElement('CropView', () => CropView)
new Vue({
  render: (h) => h('frame', [h(Home)]),
}).$start()
