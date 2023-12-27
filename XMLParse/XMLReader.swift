//
//  XMLReader.swift
//  PDFViewer-Swift
//
//  Created by kdanmobile_2 on 2023/8/14.
//

import Foundation

let kXMLReaderTextNodeKey = "text"
let kXMLReaderAttributePrefix = "@"

struct XMLReaderOptions: OptionSet {
    let rawValue: Int
    
    static let processNamespaces = XMLReaderOptions(rawValue: 1 << 0)
    static let reportNamespacePrefixes = XMLReaderOptions(rawValue: 1 << 1)
    static let resolveExternalEntities = XMLReaderOptions(rawValue: 1 << 2)
}

class XMLReader: NSObject, XMLParserDelegate {
    
    private var dictionaryStack: [NSMutableDictionary] = []
    private var textInProgress: NSMutableString = NSMutableString()
    private var errorPointer: NSError?
    
    class func dictionary(forXMLData data: Data, error: NSError) -> NSDictionary? {
        let reader = XMLReader()
        let rootDictionary = reader.object(withData: data, options: [])
        return rootDictionary
    }
    
    class func dictionary(forXMLString string: String, error: NSError) -> NSDictionary? {
        let data = string.data(using: .utf8)
        return XMLReader.dictionary(forXMLData: data!, error: error)
    }
    
    class func dictionary(forXMLData data: Data, options: XMLReaderOptions, error: NSError) -> NSDictionary? {
        let reader = XMLReader()
        let rootDictionary = reader.object(withData: data, options: options)
        return rootDictionary
    }
    
    class func dictionary(forXMLString string: String, options: XMLReaderOptions, error: NSError) -> NSDictionary? {
        let data = string.data(using: .utf8)
        return XMLReader.dictionary(forXMLData: data!, options: options, error: error)
    }
    
    func object(withData data: Data, options: XMLReaderOptions) -> NSDictionary? {
        self.dictionaryStack = [NSMutableDictionary]()
        self.textInProgress = NSMutableString()
        self.dictionaryStack.append(NSMutableDictionary())
        
        let parser = XMLParser(data: data)
        parser.delegate = self
        let success = parser.parse()
        
        if success {
            let resultDict = self.dictionaryStack[0]
            return resultDict
        }
        
        return nil
    }
    
    func parser(_ parser: XMLParser, didStartElement elementName: String, namespaceURI: String?, qualifiedName qName: String?, attributes attributeDict: [String : String] = [:]) {
        let parentDict = self.dictionaryStack.last
        
        var childDict = NSMutableDictionary()
        childDict.addEntries(from: attributeDict)
        
        if let existingValue = parentDict?[elementName] {
            var array: NSMutableArray? = nil
            if let existingArray = existingValue as? NSMutableArray {
                array = existingArray
            } else {
                array = NSMutableArray()
                array?.add(existingValue)
                parentDict?[elementName] = array
            }
            
            array?.add(childDict)
        } else {
            parentDict?[elementName] = childDict
        }
        
        self.dictionaryStack.append(childDict)
    }
    
    func parser(_ parser: XMLParser, didEndElement elementName: String, namespaceURI: String?, qualifiedName qName: String?) {
        let dictInProgress = self.dictionaryStack.last
        
        if self.textInProgress.length > 0 {
            let trimmedString = self.textInProgress.trimmingCharacters(in: .whitespacesAndNewlines)
            dictInProgress?[kXMLReaderTextNodeKey] = trimmedString
            self.textInProgress = NSMutableString()
        }
        
        self.dictionaryStack.removeLast()
    }
    
    func parser(_ parser: XMLParser, foundCharacters string: String) {
        self.textInProgress.append(string)
    }
    
    func parser(_ parser: XMLParser, parseErrorOccurred parseError: Error) {
        self.errorPointer = parseError as NSError
    }
}

