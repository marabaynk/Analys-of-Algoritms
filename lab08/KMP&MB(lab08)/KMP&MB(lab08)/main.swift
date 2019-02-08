//
//  main.swift
//  KMP&MB(lab08)
//
//  Created by Корюн Марабян on 17/12/2018.
//  Copyright © 2018 Корюн Марабян. All rights reserved.
//

import Foundation

func ZetaAlgorithm(ptrn: String) -> [Int]? {
    let pattern = Array(ptrn)
    let patternLength = pattern.count
    
    guard patternLength > 0 else {
        return nil
    }
    
    var zeta = [Int](repeating: 0, count: patternLength)
    
    var left = 0
    var right = 0
    var k_1 = 0
    var betaLength = 0
    var textIndex = 0
    var patternIndex = 0
    
    for k in 1 ..< patternLength {
        if k > right {
            patternIndex = 0
            
            while k + patternIndex < patternLength  &&
                pattern[k + patternIndex] == pattern[patternIndex] {
                    patternIndex = patternIndex + 1
            }
            
            zeta[k] = patternIndex
            
            if zeta[k] > 0 {
                left = k
                right = k + zeta[k] - 1
            }
        } else {
            k_1 = k - left + 1
            betaLength = right - k + 1
            
            if zeta[k_1 - 1] < betaLength {
                zeta[k] = zeta[k_1 - 1]
            } else if zeta[k_1 - 1] >= betaLength {
                textIndex = betaLength
                patternIndex = right + 1
                
                while patternIndex < patternLength && pattern[textIndex] == pattern[patternIndex] {
                    textIndex = textIndex + 1
                    patternIndex = patternIndex + 1
                }
                
                zeta[k] = patternIndex - k
                left = k
                right = patternIndex - 1
            }
        }
    }
    return zeta
}


extension String {
    
    func KnuthMorrisPratt(ptnr: String) -> [Int]? {
        
        let text = Array(self.characters)
        let pattern = Array(ptnr.characters)
        
        let textLength: Int = text.count
        let patternLength: Int = pattern.count
        
        guard patternLength > 0 else {
            return nil
        }
        
        var suffixPrefix: [Int] = [Int](repeating: 0, count: patternLength)
        var textIndex: Int = 0
        var patternIndex: Int = 0
        var indexes: [Int] = [Int]()
        
        
        let zeta = ZetaAlgorithm(ptrn: ptnr)
        
        for patternIndex in (1 ..< patternLength).reversed() {
            textIndex = patternIndex + zeta![patternIndex] - 1
            suffixPrefix[textIndex] = zeta![patternIndex]
        }
        
        
        textIndex = 0
        patternIndex = 0
        
        while textIndex + (patternLength - patternIndex - 1) < textLength {
            
            while patternIndex < patternLength && text[textIndex] == pattern[patternIndex] {
                textIndex = textIndex + 1
                patternIndex = patternIndex + 1
            }
            
            if patternIndex == patternLength {
                indexes.append(textIndex - patternIndex)
            }
            
            if patternIndex == 0 {
                textIndex = textIndex + 1
            } else {
                patternIndex = suffixPrefix[patternIndex - 1]
            }
        }
        
        guard !indexes.isEmpty else {
            return nil
        }
        return indexes
    }
}

extension String {
    func BoyerMoore(of pattern: String, usingHorspoolImprovement: Bool = false) -> Index? {
        let patternLength = pattern.count
        guard patternLength > 0, patternLength <= count else { return nil }
        var skipTable = [Character: Int]()
        for (i, c) in pattern.enumerated() {
            skipTable[c] = patternLength - i - 1
        }
        let p = pattern.index(before: pattern.endIndex)
        let lastChar = pattern[p]
        var i = index(startIndex, offsetBy: patternLength - 1)
        func backwards() -> Index? {
            var q = p
            var j = i
            while q > pattern.startIndex {
                j = index(before: j)
                q = index(before: q)
                if self[j] != pattern[q] { return nil }
            }
            return j
        }
        
        while i < endIndex {
            let c = self[i]
    
            if c == lastChar {
                if let k = backwards() { return k }
                
                if !usingHorspoolImprovement {
                    i = index(after: i)
                } else {
                    let jumpOffset = max(skipTable[c] ?? patternLength, 1)
                    i = index(i, offsetBy: jumpOffset, limitedBy: endIndex) ?? endIndex
                }
            } else {
                i = index(i, offsetBy: skipTable[c] ?? patternLength, limitedBy: endIndex) ?? endIndex
            }
        }
        return nil
    }
}

// A few simple tests
let str = "Hello, World"
let animals = "🐶🐔🐷🐮🐱"
let lorem = "Lorem ipsum dolor sit amet"
let somestr = "mamapakekfpafremapa"



print(animals.KnuthMorrisPratt(ptnr: "🐷🐮")!)
//print(lorem.BoyerMoore(of: "sit")!)  // 18
print(somestr.KnuthMorrisPratt(ptnr: "pa")!)
print(somestr.BoyerMoore(of: "pa")!)
