//
//  AppDelegate.swift
//  Samples
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

import UIKit
import ComPDFKit

@main
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    static let shared = AppDelegate()

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        guard let xmlFliePath = Bundle.main.path(forResource: "license_key_ios", ofType: "xml") else {
            return true
        }
        
        do {
            let error = NSError(domain: "YourDomain", code: 123, userInfo: ["key": "value"])
            let xmlData = try Data(contentsOf: URL(fileURLWithPath: xmlFliePath))
            let result = XMLReader.dictionary(forXMLData: xmlData, error: error)
            
            if let license = result?["license"] as? NSDictionary {
                if let keysDic = license["key"] as? NSDictionary {
                    if let key = keysDic["text"] as? String {
                        CPDFKit.verify(withKey: key)
                    } else {
                        print("License key can not be empty.")
                    }
                } else {
                    print("License key can not be empty.")
                }
            } else {
                print("License key can not be empty.")
            }
        } catch {
            
        }
        
        if #available(iOS 13.0, *) {
            
        } else {
            let window = UIWindow.init(frame: UIScreen.main.bounds);
            self.configWindow(window: window)
        }
        
        return true
    }
    
    func configWindow(window: UIWindow?) -> Void {
        self.window = window
        self.window?.backgroundColor = UIColor.white
        
        let filePathTest1 = Bundle.main.path(forResource: "CommonFivePage", ofType: "pdf")
        let filePathTest2 = Bundle.main.path(forResource: "PDF32000_2008", ofType: "pdf")
        let filePathTest3 = Bundle.main.path(forResource: "text", ofType: "pdf")
        let filePathTest4 = Bundle.main.path(forResource: "CreateAnnotationTest", ofType: "pdf")

        let documentFolder = NSHomeDirectory().appending("/Documents/Samples")

        if !FileManager.default.fileExists(atPath: documentFolder) {
            try? FileManager.default.createDirectory(atPath: documentFolder, withIntermediateDirectories: true, attributes: nil)
        }

        let documentURL1 = URL(fileURLWithPath: documentFolder).appendingPathComponent((filePathTest1 as NSString?)?.lastPathComponent ?? "")

        if !FileManager.default.fileExists(atPath: documentURL1.path) {
            try? FileManager.default.copyItem(at: URL(fileURLWithPath: filePathTest1 ?? ""), to: documentURL1)
        }
        
        let documentURL2 = URL(fileURLWithPath: documentFolder).appendingPathComponent((filePathTest2 as NSString?)?.lastPathComponent ?? "")

        if !FileManager.default.fileExists(atPath: documentURL2.path) {
            try? FileManager.default.copyItem(at: URL(fileURLWithPath: filePathTest2 ?? ""), to: documentURL2)
        }
        
        let documentURL3 = URL(fileURLWithPath: documentFolder).appendingPathComponent((filePathTest3 as NSString?)?.lastPathComponent ?? "")

        if !FileManager.default.fileExists(atPath: documentURL3.path) {
            try? FileManager.default.copyItem(at: URL(fileURLWithPath: filePathTest3 ?? ""), to: documentURL3)
        }
        
        let documentURL4 = URL(fileURLWithPath: documentFolder).appendingPathComponent((filePathTest4 as NSString?)?.lastPathComponent ?? "")

        if !FileManager.default.fileExists(atPath: documentURL4.path) {
            try? FileManager.default.copyItem(at: URL(fileURLWithPath: filePathTest4 ?? ""), to: documentURL4)
        }

        let viewVC = CSamplesFuctionViewController(filePaths: [documentURL1.path,documentURL2.path,documentURL3.path,documentURL4.path], password: nil)
        let navController = UINavigationController(rootViewController: viewVC)

        self.window!.rootViewController = navController
        self.window!.makeKeyAndVisible()
    }
    
    

    // MARK: UISceneSession Lifecycle
    @available(iOS 13.0, *)
    @MainActor func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    @available(iOS 13.0, *)
    @MainActor func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
    }


}

