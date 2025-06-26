//
//  AppDelegate.swift
//  PDFViewer-Swift
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
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
        let dir = Bundle.main.path(forResource: "Font", ofType: nil) ?? ""
        let fileManager = FileManager.default
        let documentDirectory = fileManager.urls(for: .documentDirectory, in: .userDomainMask).first!
        let destinationPath = documentDirectory.appendingPathComponent("Font")

        do {
            if fileManager.fileExists(atPath: destinationPath.path) {
                try fileManager.removeItem(at: destinationPath)
            }

            try fileManager.copyItem(atPath: dir, toPath: destinationPath.path)
            CPDFFont.setImportDir(destinationPath.path, isContainSysFont: true)
        } catch {
            print("Error copying Font directory: \(error)")
        }
        
        guard let xmlFliePath = Bundle.main.path(forResource: "license_key_ios", ofType: "xml") else {
            return true
        }
        
        if CPDFKitConfig.sharedInstance().annotationAuthor() == nil {
            CPDFKitConfig.sharedInstance().setAnnotationAuthor("Guest")
        }
        
        let userDefaults = UserDefaults.standard
        userDefaults.setValue(true, forKey: CPDFSaveFontSubesetKey)
        userDefaults.synchronize()
        
        CPDFKit.verify(withPath: xmlFliePath, completionHandler: { code, message in
            print("Code: \(code), Message:\(String(describing: message))")
            
            self.loadSamplesFiles()
        })
                
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
        
        let fileNames = ["ComPDFKit_Viewer_Sample_File","ComPDFKit_Document_Editor_Sample_File", "ComPDFKit_Content_Editor_Sample_File", "Password_compdfkit_Security_Sample_File", "ComPDFKit_Sample_File_iOS", "ComPDFKit_Watermark_Sample_File", "ComPDFKit_Annotations_Sample_File", "ComPDFKit_Forms_Sample_File","ComPDFKit_Signatures_Sample_File"]
        let samplesFilePaths = [VIEWERSFOLDER, DOCUMENTEDITORFOLDER, CONTENTEDITORFOLDER, SECURITYFOLDER, SAMPLESFOLDER, WATERMARKFOLDER, ANNOTATIONSFOLDER, FORMSFOLDER, SIGNATURESFOLDER]
        let fileManager = FileManager.default
        
        let guideFilePath = Bundle.main.path(forResource: "developer_guide_ios", ofType: "pdf") ?? ""
        let guideDocument = CPDFDocument(url: URL(fileURLWithPath: guideFilePath))
        
        for (fileName, docsFolderPath) in zip(fileNames, samplesFilePaths) {
            let filePath = Bundle.main.path(forResource: fileName, ofType: "pdf")
            let docsFilePath = docsFolderPath + "/" + fileName + ".pdf"
            
            if !fileManager.fileExists(atPath: docsFilePath) {
                if let filePath = filePath, fileManager.fileExists(atPath: filePath) {
                    if !fileManager.fileExists(atPath: docsFolderPath) {
                        try? FileManager.default.createDirectory(atPath: docsFolderPath, withIntermediateDirectories: true, attributes: nil)
                    }
                    
                    try? FileManager.default.copyItem(atPath: filePath, toPath: docsFilePath)
                    
                    if let index = fileNames.firstIndex(of: fileName), index < 5 {
                       
                        if fileManager.fileExists(atPath: guideFilePath) {
                            let document = CPDFDocument(url: URL(fileURLWithPath: docsFilePath))
                            
                            if document?.isLocked == true {
                                document?.unlock(withPassword: "compdfkit")
                            }
                            
                            var indexSet = IndexSet()
                            for i in 0..<(guideDocument?.pageCount ?? 0) {
                                indexSet.insert(IndexSet.Element(i))
                            }
                            
                            document?.importPages(indexSet, from: guideDocument, at: 1)
                            let userDefaults = UserDefaults.standard
                            let isSaveFontSubset = userDefaults.bool(forKey: CPDFSaveFontSubesetKey)
                            document?.write(to: URL(fileURLWithPath: docsFilePath), isSaveFontSubset: isSaveFontSubset)
                        }
                    }
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

