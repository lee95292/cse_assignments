package gradeManage;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

public class GradeDAO {

	Connection getConnect() throws ClassNotFoundException,SQLException{
		Class.forName("com.mysql.jdbc.Driver");
		
		Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/wpasgn7","root","356924qwqw!");
		
		return conn;
	}
	
	public void updateTable() throws SQLException,ClassNotFoundException{
		Connection conn;
		try {
			conn = this.getConnect();
			Statement stmt =conn.createStatement();
			String sql=null;
			
			sql = "DELETE FROM grade where id>0;";
			int a=stmt.executeUpdate(sql);
			System.out.println(a);

			conn.close();
			
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	public int addGrade(GradeBean gbean) throws SQLException, ClassNotFoundException {
			Connection conn=null;
			int res=-1;
		try {
			conn = this.getConnect();
			
			PreparedStatement pstmt = conn.prepareStatement("INSERT INTO grade(name,lab1,lab2,midterm) VALUES(?,?,?,?);");
			
			pstmt.setString(1, gbean.getName());
			pstmt.setInt(2, gbean.getLab1());
			pstmt.setInt(3, gbean.getLab2());
			pstmt.setInt(4, gbean.getMidterm());
			
			res= pstmt.executeUpdate();
			pstmt.close();
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		
		conn.close();
		return res;
	}
	
	public ArrayList<GradeBean> getGrade(){
		
		ArrayList<GradeBean> gbeanList =new ArrayList<GradeBean>();
		try {
			Connection conn = this.getConnect();
			PreparedStatement pstmt =conn.prepareStatement("select * from grade;");
			ResultSet rs = pstmt.executeQuery();
			while(rs.next()) {
				GradeBean gbean=new GradeBean();
				gbean.setName(rs.getString(2));
				gbean.setLab1(rs.getInt(3));
				gbean.setLab2(rs.getInt(4));
				gbean.setMidterm(rs.getInt(5));
				gbeanList.add(gbean);
			}	
		}catch(Exception e) {
			e.printStackTrace();
		}
		return gbeanList;
	}
	
	
}
