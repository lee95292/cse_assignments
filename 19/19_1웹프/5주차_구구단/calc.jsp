<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<title>MLEEK's Times table</title>
	<link rel="stylesheet" href="./main.css" />
</head>
<body>
	<div class="intro">
		<h1>MLEEK's Times Table</h1>
	</div>
	<form action="calc.jsp">
		<input type="text" name="num" />
		<button type="submit" value="Calculate">Calculate</button>
	</form>
	<hr>
	<%		
		int step=0;
		try{													//예상치 않은  타입에 대한 예외처리
			if(request.getParameter("num")!=null){			
				step=Integer.parseInt(request.getParameter("num"));
			}
		}catch(NumberFormatException e){
			e.printStackTrace();
			out.println("<h1>Input Integer Data</h1>");
		}
	%>
	<table id="guguTable">
	<% 		
		for(int i=1;i<=9&&step!=0;i++){
	%>
		<tr class="steps">
			<td class="cells"><%= step %>*<%= i %> =</td>
			<td class="cells"><%= step*i %></td>
		</tr>	
	<%	}
	%>
	</table>
	
	
</body>
</html>