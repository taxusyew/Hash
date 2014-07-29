var eventUtil = {
	// type 默认去掉on的类型
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
	// 删除句柄
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
	},
	getEvent: function(event){
		return event? event : window.event;
	},
	getType: function(event){
		return event.type;
	},
	getElement: function(event){
		return event.target || event.srcElement;
	},
	preventDefault: function(event){
		if(event.preventDefault){
			event.preventDefault();
		}else {
			event.returnValue = false;
		}
	},
	stopPropegation: function(event){
		if(event.stopPropegation){
			event.stopPropegation();
		}
		else{
			event.cancelBubble = true;
		}
	}
}
