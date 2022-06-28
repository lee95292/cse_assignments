package bbsService;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import bbsManage.ArticleEntity;
import bbsManage.boardDAO;

/**
 * Servlet implementation class addArticleController
 */
@WebServlet("/addArticle")
public class addArticleController extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public addArticleController() {
        super();
        // TODO Auto-generated constructor stub
    }

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		ArticleEntity article = new ArticleEntity();
		boardDAO bdao = new boardDAO();
		request.setCharacterEncoding("utf-8");
		
		article.setTitle(request.getParameter("title"));
		article.setContent( request.getParameter("content"));
		article.setName(request.getParameter("name"));
		article.setPasswd(request.getParameter("password"));
		
		try {
			bdao.addArticle(article);
		}catch(Exception e) {
			e.printStackTrace();
		}
		response.sendRedirect("./index.jsp");
	}

}
