package org.xbrlapi.impl;

import org.w3c.dom.NodeList;
import org.xbrlapi.MixedContentResource;
import org.xbrlapi.utilities.XBRLException;

/**
 * @author Geoffrey Shuetrim (geoff@galexy.net)
 */

public class MixedContentResourceImpl extends ResourceImpl implements MixedContentResource {
	
    /**
     * 
     */
    private static final long serialVersionUID = 4954206459559699372L;

    /**
     * @see org.xbrlapi.MixedContentResource#getContentAsNodeList()
     */
    public NodeList getContentAsNodeList() throws XBRLException {
    	return getDataRootElement().getChildNodes();
    }
    
    /**
     * @see org.xbrlapi.MixedContentResource#getContentAsXHTMLString()
     */
    public String getContentAsXHTMLString() throws XBRLException {
        String xml = getStore().serialize(getDataRootElement());
        xml = xml.substring(xml.indexOf(">")+1);
        String result = xml.substring(0,xml.lastIndexOf("<"));
        return result;
    }
    
}
