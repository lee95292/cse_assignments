<%@page import="bbsManage.boardDAO"%>
<%@page import="bbsManage.*"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" href="./article.css" />
<title>Insert title here</title>
</head>
<body>
	<% 
		boardDAO bdao = new boardDAO();
		ArticleEntity article =  bdao.getArticle(Integer.parseInt(request.getParameter("id")));
		
	   request.setAttribute("article", article);%>
	<div class="container">
    <form action="modArticle" method="post">
    	<input name="id" type="hidden" value="<%= article.getNum()%>"/>
    	<input name="password" type="hidden" value="<%= article.getPasswd()%>"/>
        <p class="card">title : <input name="title" type="text" value="<%=article.getTitle() %>" required></p>
        <textarea name="content"  cols="50" rows="10" required><%=article.getContent() %></textarea><br>
        <span class="card"><%=article.getName() %></span>
        <input type="submit" value="수정">
    </form>
  </div>
</body>
</html>