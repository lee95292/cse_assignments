package bbsService;

import java.io.IOException;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import bbsManage.ArticleEntity;
import bbsManage.boardDAO;

/**
 * Servlet implementation class modifyArticleController
 */
@WebServlet("/modArticle")
public class modifyArticleController extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public modifyArticleController() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		boardDAO bdao = new boardDAO();
		Map<String,String[]> map = request.getParameterMap();
		ArticleEntity article = bdao.getArticle(Integer.parseInt(request.getParameter("id")));
		request.setCharacterEncoding("utf-8");
		
		if(article.getPasswd()!=map.get("password")[0]) {
			response.getOutputStream().print("<script>alert('wrong password');location.href=history.back()</script>");
		}else if(map.isEmpty()) {
			response.getOutputStream().print("<script>alert('invalid args');location.href=history.back()</script>");
		}
		try {
				article.setTitle(map.get("title")[0]);
				article.setContent(map.get("content")[0]);
				
				bdao.modifyArticle(article);
		}catch(Exception e) {
			e.printStackTrace();
		}
			
		response.sendRedirect("./index.jsp");
	}

}
