{{>HEADER}}
{{>PAGE_HEADER}}
<div id="wrapper"> {{! Siempre necesito los dos DIVs. }}
	<div id="content">
		<h1>Config</h1>
		<form action="" method="GET">
			<p>
				<b>Var1:</b>
				<span id="var1.desc">
					<span id="var1.val">Val1</span>
					<a href="#" onclick="editVar('var1')">editar</a>
				</span>
				<span id="var1.cancelEdit" style="display:none">
					<a href="#" onclick="cancelEditVar('var1')">cancelar</a>
				</span>
			</p>
			<p>
				<b>Var2:</b>
				<span id="var2.desc">
					<span id="var2.val">Val2</span>
					<a href="#" onclick="editVar('var2')">editar</a>
				</span>
				<span id="var2.cancelEdit" style="display:none">
					<a href="#" onclick="cancelEditVar('var2')">cancelar</a>
				</span>
			</p>
			<p>
				<b>Var3:</b>
				<span id="var3.desc">
					<span id="var3.val">Val3</span>
					<a href="#" onclick="editVar('var3')">editar</a>
				</span>
				<span id="var3.cancelEdit" style="display:none">
					<a href="#" onclick="cancelEditVar('var3')">cancelar</a>
				</span>
			</p>
			<p>
				<input id="saveButton" type="submit" value="Guardar cambios" disabled="true" /> 
				<input id="cancelButton" type="button" value="Cancelar" onclick="cancelAllEditVars()" disabled="true" />
			</p>
		</form>
	</div>
</div>
{{>MENU}}
{{>FOOTER}}
