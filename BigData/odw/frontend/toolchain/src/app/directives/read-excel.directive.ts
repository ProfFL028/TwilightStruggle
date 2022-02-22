import {Directive, EventEmitter, HostListener, Output} from '@angular/core';
import {Observable, Subscriber} from 'rxjs';

import * as XLSX from 'xlsx'

@Directive({
  selector: '[appReadExcel]',
  exportAs: 'readExcel'
})
export class ReadExcelDirective {
  excelObservable: Observable<any> | undefined
  constructor() { }

  @HostListener("change", ["$event.target"])
  onChange(target: HTMLInputElement) {
    // @ts-ignore
    const file = target.files[0]
    this.excelObservable = new Observable((subscriber => {
      this.readFile(file, subscriber)
    }))
  }

  readFile(file: File, subscriber: Subscriber<any>) {
    const fileReader = new FileReader()
    fileReader.readAsArrayBuffer(file)
    fileReader.onload = (e)=> {
      // @ts-ignore
      const bufferArray = e.target.result
      const wb: XLSX.WorkBook = XLSX.read(bufferArray, {type: 'buffer'})
      const wsName: String = wb.SheetNames[0]
      // @ts-ignore
      const ws: XLSX.WorkSheet = wb.Sheets[wsName]
      const data = XLSX.utils.sheet_to_html(ws)
      subscriber.next(data)
      subscriber.complete()
    }
  }
}
