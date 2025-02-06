import { View } from '@nativescript/core';

export class CropView extends View {
  createNativeView() {
    if (global.isAndroid) {
      return new com.akylas.documentscanner.CropView(this._context);
    } else if (global.isIOS) {
      return NSCropView.alloc().init();
    }
    return null;
  }

  set quads(value: any) {
    console.warn('set quads')
    const nativeView = this.nativeViewProtected;
    if (nativeView) {
      nativeView.quads = null;
      if (global.isAndroid) {
        (nativeView as android.view.View).invalidate();
      } else {
        (nativeView as UIView).setNeedsDisplay();
      }
    }
  }

  callSomething() {
    console.error('called')
  }
}
