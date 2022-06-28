package bbsManage;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
public class boardDAO {
	Connection getConnect()throws SQLException, ClassNotFoundException{
		Class.forName("com.mysql.jdbc.Driver");
		Connection conn= DriverManager.getConnection("jdbc:mysql://localhost/wpasgn7","root","356924qwqw!");
		
		return conn;
	}
	
	public int addArticle(ArticleEntity article)throws SQLException, ClassNotFoundException{
		int res= -1;
		try {
			Connection conn = this.getConnect();
			
			String sql = "INSERT INTO bbs(title,content,name,password) values(?,?,?,?);";
			PreparedStatement pstmt= conn.prepareStatement(sql);
			pstmt.setString(1, article.getTitle());
			pstmt.setString(2, article.getContent());
			pstmt.setString(3, article.getName());
			pstmt.setString(4, article.getPasswd());
			
			res=pstmt.executeUpdate();
		}catch(Exception e) {
			e.printStackTrace();
		}
		return res;
	}
	
	public int modifyArticle(ArticleEntity article) throws SQLException, ClassNotFoundException{
		int res=-1;
		try {
			Connection conn = this.getConnect();
			String sql = "update bbs set title=?,content=? where id=?";
			
			PreparedStatement pstmt = conn.prepareStatement(sql);
			pstmt.setString(1, article.getTitle());
			pstmt.setString(2, article.getContent());
			pstmt.setInt(3, article.getNum());
			
			res=pstmt.executeUpdate();
		}catch(Exception e){
			e.printStackTrace();
		}
		return res;
	}
	public ArrayList<ArticleEntity> getArticleList(int page)throws SQLException, ClassNotFoundException{
		ArrayList<ArticleEntity> articleList= null;
		ArticleEntity article = null;
		try {
			Connection conn = this.getConnect();
			String sql = "SELECT * FROM bbs order by id desc limit ?,8;";
			PreparedStatement pstmt= conn.prepareStatement(sql);
			
			pstmt.setInt(1, page*8);
			
			ResultSet rs =pstmt.executeQuery();
			
			while(rs.next()) {
				if(articleList==null)articleList =new ArrayList<>();
				article = new ArticleEntity();
				article.setNum(rs.getInt(1));
				article.setTitle(rs.getString(2));
				article.setContent(rs.getString(3));
				article.setName(rs.getString(4));
				article.setPasswd(rs.getString(5));
				article.setDate(rs.getDate(6));
				articleList.add(article);
			}
		}catch (Exception e) {
			e.printStackTrace();
		}
		return articleList;
	}
	
	public ArticleEntity getArticle(int num) {
		ArticleEntity article = null;
		try {
			Connection conn =this.getConnect();
			
			String sql = "select * from bbs where id=?";
			PreparedStatement pstmt = conn.prepareStatement(sql);
			
			pstmt.setInt(1, num);
			
			ResultSet rs = pstmt.executeQuery();
			if(rs.next()) {
				article= new ArticleEntity();
				article.setNum(rs.getInt(1));
				article.setTitle(rs.getString(2));
				article.setContent(rs.getString(3));
				article.setName(rs.getString(4));
				article.setPasswd(rs.getString(5));
				article.setDate(rs.getDate(6));
			}
		}catch (Exception e) {
			e.printStackTrace();
		}
		return article;
		
	}
}
