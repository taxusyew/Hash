var eventUtil = {
	// type Ĭ��ȥ��on������
	addHandler:function(element, type, handler){
		if(element.addEventListener){
			// DOM2
			element.addEventListener(type, handler, false);
		}else if(element.attachEvent){
			// IE
			element.attachEvent('on' +type, handler);
		}else{
			// DOM0
			element['on'+type] = handler;
		}
	},
	// ɾ�����
	removeHandler:function(element, type, handler){
		if(element.removeEventListener){
			// DOM2
			element.removeEventListener(type, handler, false);
		}else if(element.detachEvent){
			// IE
			element.detachEvent('on' +type, handler);
		}else{
			// DOM0
			element['on'+type] = null;
		}
	}
}