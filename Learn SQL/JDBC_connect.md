```java

package src;

import java.sql.*;

public class Driver {

	public static void main(String[] args) {
		String url = "jdbc:mysql://localhost:3306/demo?useUnicode"
				+ "=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
		String user = "user";
		String password = "password";

		try {
			Connection connection = DriverManager.getConnection(url, user, password);
			Statement myStatement = connection.createStatement();

			ResultSet myResult = myStatement.executeQuery("select * from students");

			while (myResult.next()) {
				System.out.println(myResult.getInt("age") + " , " + myResult.getString("name"));
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}

```