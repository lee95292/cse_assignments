<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="userManage.UserDAO" %>
<%@ page import="userManage.UserBean" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<%
	UserDAO dao = new UserDAO();
	UserBean user = new UserBean();
	
	user.setId(request.getParameter("id"));
	user.setPassword(request.getParameter("pw"));
	int res= dao.getUser(user);
	
	if(res==1){
		session.setAttribute("id", user.getId());
		response.sendRedirect("./main.html");
	}

%>
<script>
	alert('login failed!');
	location.href="./index.html";
</script>

</body>
</html>