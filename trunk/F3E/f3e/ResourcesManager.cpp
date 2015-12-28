#include "ResourcesManager.h"

#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

ResourcesManager::ResourcesManager(void)
{
}


ResourcesManager::~ResourcesManager(void)
{
}

void ResourcesManager::loadAssetSet( std::string filename )
{
	xercesc::XMLPlatformUtils::Initialize();

	xercesc::XercesDOMParser* parser = NULL;
	
	//setup parser
	parser = new xercesc::XercesDOMParser();
	
	parser->setDoNamespaces(false);
	parser->setDoNamespaces(false);
	parser->setDoSchema(false);

	//start reading
	parser->parse(filename.c_str());

	xercesc::DOMDocument* document = parser->getDocument();
	xercesc::DOMElement* root = document->getDocumentElement();

	std::cout << root->getChildNodes()->getLength();

	xercesc::XMLPlatformUtils::Terminate();


}
