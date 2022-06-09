const TreeNode = {

    left: undefined,
    right: undefined,
    value: null
}


function insert(node, value) {
    if (node.value) {
        if (value > node.value){
            insert(node.right, value);
        }else{
            insert(node.left, value);
        }
    }else{
        node.value = value;
        node.left = null;
        node.right = null;
    }
}

function remove(node, name){
    if(node === null || node === undefined){
        return null;
    }else{
        if(node.value === name){

            if(node.left === null && node.right === null){
                return null;                
            }
        }else{
            if(name < node.value){
                node.left = remove(node.left, name);
            }else{
                node.right = remove(node.right, name);
            }
            return node;
        }

    }
}