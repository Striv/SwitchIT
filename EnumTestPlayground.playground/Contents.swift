//: Playground - noun: a place where people can play

import UIKit
import Alamofire

enum Command {
    case on, off, blink
}

func printCommand(c: Command){
    print("The command is: " + String(describing: c))
}

func printString(index: Int, c: Command) {
    let subURL = "/" + String(describing: index)  + "/" + String(describing: c)
    
    print(subURL)
}

printString(index: 3, c: Command.blink)


