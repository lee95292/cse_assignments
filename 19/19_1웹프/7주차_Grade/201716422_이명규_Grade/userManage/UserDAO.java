package userManage;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDAO {

	
	public UserDAO() {
		makeUserTable();
	}

	Connection getConnect() throws ClassNotFoundException,SQLException {
		Class.forName("com.mysql.jdbc.Driver");
		
		Connection conn= DriverManager.getConnection("jdbc:mysql://localhost/wpasgn7","root","356924qwqw!");
		
		return conn;
	}
	public void makeUserTable() {
		Connection conn =null;
		try {
			conn=this.getConnect();
			PreparedStatement pstmt = conn.prepareStatement("show tables like 'user';");
			ResultSet rs =pstmt.executeQuery();
			
			if(!rs.next()) {
				pstmt=conn.prepareStatement("CREATE TABLE user("
						+ "number INT(10) PRIMARY KEY AUTO_INCREMENT,"
						+ "id VARCHAR(20) ,"
						+ "password VARCHR(40) );");
			}
			
			pstmt.executeQuery();
			conn.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	public int getUser(UserBean user)throws ClassNotFoundException,SQLException {
		Connection conn=null;
		
		try {
			conn=this.getConnect();
			
			PreparedStatement pstmt =conn.prepareStatement("select * from user where id=? and password=?;");
			pstmt.setString(1, user.getId());
			pstmt.setString(2, user.getPassword());
			
			ResultSet rs=pstmt.executeQuery();
			if(rs.next())return 1;
			else return -1;
		}catch(Exception e) {
			e.printStackTrace();
		}
		
		return -1;
	}
	
	
}
