Blockly.Blocks['open_gate_with_speed'] = {
  init: function () {
    this.appendDummyInput()
        .appendField('open gate at speed');
    this.appendValueInput('SPEED')
        .setCheck('Number');
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(160);
    this.setTooltip('Opens the gate. Speed 1 (slow) to 10 (fast).');
  }
};

Blockly.JavaScript['open_gate_with_speed'] = function (block) {
  var speed = Blockly.JavaScript.valueToCode(
    block, 'SPEED', Blockly.JavaScript.ORDER_ATOMIC
  ) || '5';

  var code = '(function() {\n'
           + '  var speed = Math.min(10, Math.max(1, ' + speed + '));\n'
           + '  var stepDelay = Math.round(55 - speed * 5);\n'
           + '  for (var angle = 0; angle <= 90; angle++) {\n'
           + '    servo.write(angle);\n'
           + '    delay(stepDelay);\n'
           + '  }\n'
           + '})();\n';

  return code;
};
