//
//  API.swift
//  SwitchIT
//
//  Created by Dan on 12/21/16.
//  Copyright © 2016 DevexNJ. All rights reserved.
//


import Foundation
import Alamofire

let URL = "http://192.168.1.200"

enum Command {
    case on, off, blink, toggle, status
}


func getAll(callback: @escaping (Int) -> ()){
    let subURL = "/all/status"
    Alamofire.request(URL+subURL, method: .get, encoding: JSONEncoding.default).responseString { response in
        if response.response?.statusCode != 200 {
            print("Error fetching " + subURL)
            callback(404)
        }
        else {
            let a = response.result.value?.data(using: String.Encoding.utf8)
            print(a)
            callback(200)
        }
    }
}

func getOne(index: Int, callback: @escaping (Int) -> ()){
    let subURL = "/" + String(describing: index) + "/status"
    Alamofire.request(URL+subURL, method: .get, encoding: JSONEncoding.default).responseString { response in
        if response.response?.statusCode != 200 {
            print("Error fetching " + subURL)
            callback(404)
        }
        else {
            let a = response.result.value?.data(using: String.Encoding.utf8)
            print(a)
            callback(200)
        }
    }
}

func setAll(command: Command, callback: @escaping (Int) -> ()){
    let subURL = "/all/" + String(describing: command)
    Alamofire.request(URL+subURL, method: .get, encoding: JSONEncoding.default).responseString { response in
        if response.response?.statusCode != 200 {
            print("Error fetching " + subURL)
            callback(404)
        }
        else {
            let a = response.result.value?.data(using: String.Encoding.utf8)
            print(a)
            callback(200)
        }
    }
}

func setOne(index: Int, command: Command, callback: @escaping (Int) -> ()){
    let subURL = "/" + String(describing: index)  + "/" + String(describing: command)
    Alamofire.request(URL+subURL, method: .get, encoding: JSONEncoding.default).responseString { response in
        if response.response?.statusCode != 200 {
            print("Error fetching " + subURL)
            callback(404)
        }
        else {
            let a = response.result.value?.data(using: String.Encoding.utf8)
            print(a)
            callback(200)
        }
    }
}
