var toolbox = {
  kind: 'flyoutToolbox',
  contents: [
    { kind: 'block', type: 'math_number' },
    { kind: 'block', type: 'open_gate_with_speed' }
  ]
};

var workspace = Blockly.inject('blocklyDiv', {
  toolbox: toolbox
});

function generateCode() {
  var code = Blockly.JavaScript.workspaceToCode(workspace);
  document.getElementById('output').textContent = code;
}
