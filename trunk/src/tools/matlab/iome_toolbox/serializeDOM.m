function s = serializeDOM(x)
% Serialization through tranform.
domSource = javax.xml.transform.dom.DOMSource(x);
tf = javax.xml.transform.TransformerFactory.newInstance;
serializer = tf.newTransformer;
serializer.setOutputProperty(javax.xml.transform.OutputKeys.ENCODING,'utf-8');
serializer.setOutputProperty(javax.xml.transform.OutputKeys.INDENT,'yes');

stringWriter = java.io.StringWriter;
streamResult = javax.xml.transform.stream.StreamResult(stringWriter);

serializer.transform(domSource, streamResult);
s = char(stringWriter.toString);

