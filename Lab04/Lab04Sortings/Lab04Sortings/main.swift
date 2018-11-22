//
//  main.swift
//  Lab04Sortings
//
//  Created by Корюн Марабян on 18/11/2018.
//  Copyright © 2018 Корюн Марабян. All rights reserved.
//

import Foundation
import Cocoa

////////////////Слиянием//////////////////////////
func mergeSort<T: Comparable>(_ array: [T]) -> [T] {
    guard array.count > 1 else { return array }
    let middleIndex = array.count / 2
    let leftArray = mergeSort(Array(array[0..<middleIndex]))
    let rightArray = mergeSort(Array(array[middleIndex..<array.count]))
    return merge(leftPile: leftArray, rightPile: rightArray)
}

func merge<T: Comparable>(leftPile: [T], rightPile: [T]) -> [T] {
    var leftIndex = 0
    var rightIndex = 0
    var orderedPile: [T] = []
    if orderedPile.capacity < leftPile.count + rightPile.count {
        orderedPile.reserveCapacity(leftPile.count + rightPile.count)
    }
    
    while true {
        guard leftIndex < leftPile.endIndex else {
            orderedPile.append(contentsOf: rightPile[rightIndex..<rightPile.endIndex])
            break
        }
        guard rightIndex < rightPile.endIndex else {
            orderedPile.append(contentsOf: leftPile[leftIndex..<leftPile.endIndex])
            break
        }
        
        if leftPile[leftIndex] < rightPile[rightIndex] {
            orderedPile.append(leftPile[leftIndex])
            leftIndex += 1
        } else {
            orderedPile.append(rightPile[rightIndex])
            rightIndex += 1
        }
    }
    
    
    return orderedPile
}
/////////////////////////////////////////////////

////////////////////////Шелл////////////////////

func insertionSort(_ list: inout [Int], start: Int, gap: Int) {
    for i in stride(from: (start + gap), to: list.count, by: gap) {
        let currentValue = list[i]
        var pos = i
        while pos >= gap && list[pos - gap] > currentValue {
            list[pos] = list[pos - gap]
            pos -= gap
        }
        list[pos] = currentValue
    }
}

func shellSort(_ list: inout [Int]) {
    var sublistCount = list.count / 2
    while sublistCount > 0 {
        for pos in 0..<sublistCount {
            insertionSort(&list, start: pos, gap: sublistCount)
        }
        sublistCount = sublistCount / 2
    }
}
////////////////////////////////////////////////

///////////////Вставка/////////////////////////
func insertionSort<T: Comparable>(_ array: [T]) -> [T] {
    var a = array
    for x in 1..<a.count {
        var y = x
        let temp = a[y]
        while y > 0 && temp < a[y - 1] {
            a[y] = a[y - 1]
            y -= 1
        }
        a[y] = temp
    }
    return a
}
/////////////////////////////////////////////

//Массив, отсортированный по возрастанию
for i in stride(from: 100, to: 1100, by: 100){
    
    var firstArr = [Int] (1...i)
    
    var totalTime: Double = 0
    var totalTime2: Double = 0
    var totalTime3: Double = 0
    
    var avgTime:Double = 0
    var avgTime2:Double = 0
    var avgTime3:Double = 0
    for _ in 1...100{
        let begin = clock()
        shellSort(&firstArr)
        let diff = Double(clock() - begin) / Double(CLOCKS_PER_SEC) * 1000
        
        let begin2 = clock()
        insertionSort(firstArr)
        let diff2 = Double(clock() - begin2) / Double(CLOCKS_PER_SEC) * 1000
        
        let begin3 = clock()
        mergeSort(firstArr)
        let diff3 = Double(clock() - begin3) / Double(CLOCKS_PER_SEC) * 1000
        
        totalTime =  totalTime + diff
        totalTime2 =  totalTime2 + diff2
        totalTime3 =  totalTime3 + diff3
    }
    avgTime = totalTime/100
    avgTime2 = totalTime2/100
    avgTime3 = totalTime3/100
    
    //print("For \(i) elements avgTime(Shell) is \(String(format: "%.3f", avgTime))")
    //print("For \(i) elements avgTime(Insertion) is \(String(format: "%.3f", avgTime2))" )
    //print("For \(i) elements avgTime(Merge) is \(String(format: "%.3f", avgTime3))\n" )

}

//Массив, отсортированный по убыванию
for i in stride(from: 100, to: 1100, by: 100){
    
    var secondArr = [Int] ((1...i).reversed())
    
    var totalTimeMerge: Double = 0
    var totalTimeShell: Double = 0
    var totalTimeInsertion: Double = 0
    
    var avgTimeMerge:Double = 0
    var avgTimeShell:Double = 0
    var avgTimeInsertion:Double = 0
    
    for _ in 1...100{
        let beginMerge = clock()
        shellSort(&secondArr)
        let diffMerge = Double(clock() - beginMerge) / Double(CLOCKS_PER_SEC) * 1000
        
        let beginShell = clock()
        insertionSort(secondArr)
        let diffShell = Double(clock() - beginShell) / Double(CLOCKS_PER_SEC) * 1000
        
        let beginInsertion = clock()
        mergeSort(secondArr)
        let diffInsertion = Double(clock() - beginInsertion) / Double(CLOCKS_PER_SEC) * 1000
        
        totalTimeMerge =  totalTimeMerge + diffMerge
        totalTimeShell =  totalTimeShell + diffShell
        totalTimeInsertion =  totalTimeInsertion + diffInsertion
    }
    avgTimeMerge = totalTimeMerge/100
    avgTimeShell = totalTimeShell/100
    avgTimeInsertion = totalTimeInsertion/100
    
    //print("For \(i) elements avgTime(Merge) is \(String(format: "%.3f", avgTimeMerge))")
    //print("For \(i) elements avgTime(Shell) is \(String(format: "%.3f", avgTimeShell))" )
    //print("For \(i) elements avgTime(Insertion) is \(String(format: "%.3f", avgTimeInsertion))\n" )
    
}

//Массив, заполненный рандомными целыми числами

for i in stride(from: 100, to: 1100, by: 100){
    var thirdArr = [Int] (1...i)
    thirdArr.append(Int.random(in: 1...100))
    
    var totalTimeMerge2: Double = 0
    var totalTimeShell2: Double = 0
    var totalTimeInsertion2: Double = 0
    
    var avgTimeMerge2:Double = 0
    var avgTimeShell2:Double = 0
    var avgTimeInsertion2:Double = 0
    
    for _ in 1...100{
        let beginMerge2 = clock()
        shellSort(&thirdArr)
        let diffMerge2 = Double(clock() - beginMerge2) / Double(CLOCKS_PER_SEC) * 1000
        
        let beginShell2 = clock()
        insertionSort(thirdArr)
        let diffShell2 = Double(clock() - beginShell2) / Double(CLOCKS_PER_SEC) * 1000
        
        let beginInsertion2 = clock()
        mergeSort(thirdArr)
        let diffInsertion2 = Double(clock() - beginInsertion2) / Double(CLOCKS_PER_SEC) * 1000
        
        totalTimeMerge2 =  totalTimeMerge2 + diffMerge2
        totalTimeShell2 =  totalTimeShell2 + diffShell2
        totalTimeInsertion2 =  totalTimeInsertion2 + diffInsertion2
    }
    avgTimeMerge2 = totalTimeMerge2/100
    avgTimeShell2 = totalTimeShell2/100
    avgTimeInsertion2 = totalTimeInsertion2/100
    
    //print("For \(i) elements avgTime(Merge) is \(String(format: "%.3f", avgTimeMerge2))")
    //print("For \(i) elements avgTime(Shell) is \(String(format: "%.3f", avgTimeShell2))" )
    //print("For \(i) elements avgTime(Insertion) is \(String(format: "%.3f", avgTimeInsertion2))\n" )
    
}
