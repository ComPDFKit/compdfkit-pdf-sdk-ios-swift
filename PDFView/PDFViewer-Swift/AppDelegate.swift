//
//  AppDelegate.swift
//  PDFViewer-Swift
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
import ComPDFKit_Tools

@main
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    static let shared = AppDelegate()

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        guard let xmlFliePath = Bundle.main.path(forResource: "license_key_ios", ofType: "xml") else {
            return true
        }
        
        loadSamplesFiles()
        
        do {
            let error: NSError = NSError()
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

        let homeController = CHomeViewController.init(nibName: nil, bundle: nil)

        let navController = CNavigationController(rootViewController: homeController)

        self.window!.rootViewController = navController
        self.window!.makeKeyAndVisible()
    }
    
    private func loadSamplesFiles() {
        
        let fileNames = ["ComPDFKit_Viewer_Sample_File", "ComPDFKit_Annotations_Sample_File", "ComPDFKit_Forms_Sample_File", "ComPDFKit_Signatures_Sample_File","ComPDFKit_Document_Editor_Sample_File", "ComPDFKit_Content_Editor_Sample_File", "Password_compdfkit_Security_Sample_File", "ComPDFKit_Watermark_Sample_File", "ComPDFKit_Sample_File_iOS"]
        let samplesFilePaths = [VIEWERSFOLDER, ANNOTATIONSFOLDER, FORMSFOLDER, SIGNATURESFOLDER, DOCUMENTEDITORFOLDER, CONTENTEDITORFOLDER, SECURITYFOLDER, WATERMARKFOLDER, SAMPLESFOLDER]
        let fileManager = FileManager.default
        
        for (fileName, docsFolderPath) in zip(fileNames, samplesFilePaths) {
            let filePath = Bundle.main.path(forResource: fileName, ofType: "pdf")
            let docsFilePath = docsFolderPath + "/" + fileName + ".pdf"
            
            if !fileManager.fileExists(atPath: docsFilePath) {
                if let filePath = filePath, fileManager.fileExists(atPath: filePath) {
                    if !fileManager.fileExists(atPath: docsFolderPath) {
                        try? FileManager.default.createDirectory(atPath: docsFolderPath, withIntermediateDirectories: true, attributes: nil)
                    }
                    
                    try? FileManager.default.copyItem(atPath: filePath, toPath: docsFilePath)
                }
            }
        }
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

