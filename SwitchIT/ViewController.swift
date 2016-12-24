//
//  ViewController.swift
//  SwitchIT
//
//  Created by Dan on 12/21/16.
//  Copyright © 2016 DevexNJ. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet var b1: UIButton!
    @IBOutlet var b2: UIButton!
    @IBOutlet var b3: UIButton!
    @IBOutlet var b4: UIButton!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


    @IBAction func b1_clicked(_ sender: Any) {
        setOne(index: 1, command: Command.toggle, callback: {statusCode in })
    }
    
    @IBAction func b2_clicked(_ sender: Any) {
        setOne(index: 2, command: Command.toggle, callback: {statusCode in})
    }
    
    @IBAction func b3_clicked(_ sender: Any) {
        setOne(index: 3, command: Command.toggle, callback: {statusCode in})
    }
    
    @IBAction func b4_clicked(_ sender: Any) {
        setOne(index: 4, command: Command.toggle, callback: {statusCode in})
    }
    
    @IBAction func all_off_clicked(_ sender: Any) {
        setAll(command: Command.off, callback: {statusCode in})
    }
    
    @IBAction func all_on_clicked(_ sender: Any) {
        setAll(command: Command.on, callback: {statusCode in})
    }
}

