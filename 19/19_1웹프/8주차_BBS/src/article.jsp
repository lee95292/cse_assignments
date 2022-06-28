<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="bbsManage.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<link rel="stylesheet" href="./article.css" />
<% 
	int articleNum = Integer.parseInt(request.getParameter("anum"));
	if(articleNum<=0 || request.getParameter("anum") ==null ){	
		out.print("<script>alert('invalid access');location.href=history.back()</script>");
		return;
	}
	boardDAO bdao = new boardDAO();
	ArticleEntity article = bdao.getArticle(articleNum);
%>
</head>
<body>
		<div class="container">
			<h2><%= article.getTitle() %></h2>
			<p style="text-align:right"><%= article.getDate() %></p>
			<hr />
			<div class="content">
				<%= article.getContent() %>
			</div>
			<div class="user">
				<form action="modify.jsp">
					<p id="userid"><%=article.getName() %></p>
					<input name = "id" type="hidden" value="<%= article.getNum()%>"/>
					<input name = password type="password" required />
					<input type="submit" value="수정" />
				</form>
			</div>
		</div>
</body>
</html>