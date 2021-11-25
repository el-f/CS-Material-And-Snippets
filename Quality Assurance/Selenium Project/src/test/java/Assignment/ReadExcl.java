package Assignment;


import java.io.File;
import java.io.FileInputStream;

import java.io.IOException;

import org.apache.poi.hssf.usermodel.HSSFWorkbook;

import org.apache.poi.ss.usermodel.Sheet;

import org.apache.poi.ss.usermodel.Workbook;

public class ReadExcl {

    public static int rowCount;
    public static Sheet guru99Sheet;

    public static void readExcel(String filePath, String fileName, String sheetName) throws IOException {

        //Create an object of File class to open xlsx file
        String path = (filePath.isEmpty() ? "" : filePath + "/") + fileName;
        File file = new File(path);

        //Create an object of FileInputStream class to read excel file

        FileInputStream inputStream = new FileInputStream(file);

        Workbook guru99Workbook = null;

        //Find the file extension by splitting file name in substring  and getting only extension name

        String fileExtensionName = fileName.substring(fileName.indexOf("."));

        //Check condition if the file is xlsx file

        //  if(fileExtensionName.equals(".xlsx")){

        //If it is xlsx file then create object of XSSFWorkbook class

        // guru99Workbook = new Workbook(inputStream);

        //  }

        //Check condition if the file is xls file

        if (fileExtensionName.equals(".xls")) {

            //If it is xls file then create object of HSSFWorkbook class

            guru99Workbook = new HSSFWorkbook(inputStream);

        }

        //Read sheet inside the workbook by its name

        assert guru99Workbook != null;
        guru99Sheet = guru99Workbook.getSheet(sheetName);

        //Find number of rows in excel file

        rowCount = guru99Sheet.getLastRowNum() - guru99Sheet.getFirstRowNum();


    }

    public static String getStringFromCell(int row_number, char col_letter) {
        return guru99Sheet.getRow(row_number - 1).getCell(col_letter - 'A').getStringCellValue();
    }

    //get string value of numeric cell
    public static String getIntegerFromCell(int row_number, char col_letter) {
        return String.valueOf((int) guru99Sheet.getRow(row_number - 1).getCell(col_letter - 'A').getNumericCellValue());
    }

    public static int getRowcount() {
        return rowCount;
    }

    public static Sheet getSheet() {
        return guru99Sheet;
    }
}




