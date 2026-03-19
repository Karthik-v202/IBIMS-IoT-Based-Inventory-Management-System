function doGet(e) {
  var Sheets = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();

  var Time = new Date();

  var ItemStatus = e.parameter.status;
  var SensorValue = e.parameter.val;
  Sheets.appendRow([Time, ItemStatus, SensorValue]);

  return ContentService.createTextOutput("Data Logged Succesfully");
}
