<template>
  <Page>
    <GridLayout class="camera-view-wrapper">
      <CameraView @tap="onCameraTap"
                  @loaded="setCameraViewRef"
                  @unloaded="cameraViewRef = null"
                  class="camera-view"
                  :readyToStartPreview="true"
      />
      <Img :src="imageSource" verticalAlignment="bottom" height="100" width="100"/>
      <CropView ref="cropview" @loaded="setCropViewRef"/>
      <Button row="1" horizontalAlignment="center" text="photo_camera" class="icon-only plain height-40" @tap="takePicture"/>
      <Button row="1" horizontalAlignment="left" text="toggle" class="plain height-40" @tap="toggleCamera"/>
      <Button row="1" horizontalAlignment="right" text="Proz" class="plain height-40" @tap="applyProcessor"/>
    </GridLayout>
  </Page>
</template>

<script>
import {checkMultiple, check, request} from "@nativescript-community/perms";
import { View, ImageSource } from '@nativescript/core';
export default {
  name: "Home",
  data() {
    return {
      cameraViewRef: null,
      cropViewRef: null,
      imageSource: null,
      readyToStartPreview: false
    }
  },
  async mounted() {
    console.warn(NSCropView)
    const requestPermResult = await request('camera')
    if(requestPermResult === 'authorized') {
      this.readyToStartPreview = true
    }
  },
  methods: {
    setCropViewRef(args) {
      this.cropViewRef = args.object
    },
    async applyProcessor() {
      try {
        if (__ANDROID__) {
          const processor = new com.nativescript.cameraviewdemo.CustomImageAnalysisCallback(cameraView.nativeView._context, cropView.nativeView.nativeViewProtected);
          this.cameraViewRef.processor = processor;
        } else {
          this.cameraViewRef.processor = OpencvDocumentProcessDelegate.alloc().initWithCropView(this.cropViewRef.nativeViewProtected)
          console.warn(this.cameraViewRef.processor)
        }
      } catch (error) {
        console.error(error);
      }
    },
    setCameraViewRef(args) {
      this.cameraViewRef = args.object
      // this.cameraViewRef.startPreview()
    },
    onCameraTap(event) {
      this.cameraViewRef?.focusAtPoint(event.getX(), event.getY())
    },
    toggleCamera() {
      if(!this.cameraViewRef) {
        return
      }
      this.cameraViewRef.toggleCamera()
    },
    torchCamera() {
      if(!this.cameraViewRef) {
        return
      }
      console.warn(this.cameraViewRef.flashMode)
      this.cameraViewRef.flashMode = 'torch'
    },
    async takePicture() {
      if(!this.cameraViewRef) {
        return
      }
      const {image, info} = await this.cameraViewRef.takePicture({savePhotoToDisk: false})
      this.imageSource = new ImageSource(image)
    }
  }
}
</script>

<style>
.camera-view-wrapper {
  rows: *, 70;
  padding-bottom: 80;
}
.camera-view-wrapper .camera-view {
  row: 0;
  height: 100%;
  width: 100%;
}
</style>
